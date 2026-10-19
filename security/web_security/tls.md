# TLS

* Asymmetric encryption solves the problem of agreeing on a key with a stranger, but it is slow.
* Symmetric encryption is fast, but both sides need the same key first.

1. **The server proves who it is.**
    * It sends its certificate. A certificate is a document that says "domain `bank.co` has public key X" signed by a
      certificate authority.
    * The browser comes with the certficates, that is the public keys, of authorities it trusts.
    * The browser checks the authority signature on the certificate with the authority's public key and checks if the
      domain in the certificate is the site it wanted.
2. **The two sides agree on a session key.**
    * Both sides contribute fresh random values to the handshake, the server signs the handshake data with thos values
      provided with its private key.
    * The browser checks the signature with the public key from the certificate. Only the server could sign it and the
      values cannot be replayed.
    * Finally, both sides send each other a public value, each one combines it with a secret only it holds and both
      arrive at the same symmetric key (see Diffle-Hellman algorithm for details).
3. **The rest of the connection is symmetric.**

So there are two signature checks in TLS:

* The authority's public key verifies the signature in the certificate ("this key belongs to this domain").
* The certificate's public key verifies the handshake ("this must be the server I am talking to, only it has the private
  key").