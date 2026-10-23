# TLS

* Asymmetric encryption solves the problem of agreeing on a key with a stranger, but it is slow.
* Symmetric encryption is fast, but both sides need the same key first.

## Diffie-Hellman algorithm

Important part about the TLS key sharing.

**Two entities are talking over a line anyone can read and still end up with the same secret key, without ever sending
that key.**

Before (TLS 1.2):

* Browser made up a key, encrypted it with the server's public key and sent it.
* Disadvantages: the secret **travels** - encrypted, but still. If the private key leaks, someone could decrypt recorded
  conversations.

Now:

* With DH, the secret never travels.
* The secrets are thrown away after the connection. There is no way do decrypt a recorded conversation, even if the
  server's private key leaks later.

How it works:

1. Browser and server know two public numbers: `g = 5` and `p = 23`. The eavesdropper knows them too.
2. The browser picks a secret `a = 4`. It never sends it.
3. The server picks a secret `b = 3`. It never sends it.
4. The browser computes its key share using the DH formula: `5^4 mod(23) = 625 mod(23) = 4`.
5. Browser sends `4` in `ClientHello`. The eavesdropper sees it.
6. Server does the same computation: `5^3 mod(23) = 125 mod (23) = 10`.
7. Browser sends `10` in `ServerHello`. The eavesdropper sees it.
8. The browser takes the server's share to its own secret: `10^4 mod(23) = 10,000 mod(23) = 18`.
9. The server takes the browser's share to its own secret: `4^3 mod(23) = 64 mod(23) = 18`.
10. They get the same values, because they virtually did this computation:
    * Browser: `10^4 mod(23) = [5^3 mod(23)]^4 mod(23) = [5^3]^4 mod(23) = 5^12 mod(23)`.
    * Server: `4^3 mod (23) = [5^4 mod(23)]^3 mod(23) = [5^4]^3 mod(23) = 5^12 mod(23)`.
11. **Both have 18 and 18 never went over the wire.**

What the eavesdropper heard and what they can do:

1. They first heard 5 and 23.
2. Then they heard 4 from browser.
3. Then they heard 10 from the server.
4. They need either a or b, meaning which x gives `5^x mod 23 = 4`. This is easy with 23 and infeasible with a 2048-bit
   `p` value.

## Flow

1. **Hello**
    * Browser sends a `ClientHello` request to server:
        * Browser random value. This makes every handshake unique, so a recorded one cannot be replayed.
        * Browser key share. Mentioned above.
        * Set of accepted ciphers.
        * Requested domain.
    * Server responds with `ServerHello`:
        * Server random value.
        * Server key share.
        * Chosen cipher.
    * Each side combines the other's shares with its own secret and get the same secret (described above).
2. **Server proves who they are, encrypted symetrically**
    1. Check 1 - check of the certificate and domain.
        * Server sends its certificate. A certificate is a document that says "domain `bank.co` has public key X" signed
          by a certificate authority.
        * The browser comes with the certficates, that is the public keys, of authorities it trusts.
        * The browser checks the authority signature on the certificate with the authority's public key and checks if
          the domain in the certificate is the site it wanted.
    2. Check 2 - server proves that it holds a private key for that certificate by signing the handshake including both
       key shares and randoms.
3. **The rest of the connection is symmetric.**

So there are two signature checks in TLS:

* The authority's public key verifies the signature in the certificate ("this key belongs to this domain").
* The certificate's public key verifies the handshake ("this must be the server I am talking to, only it has the private
  key").