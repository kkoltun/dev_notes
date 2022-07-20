Triggers:

* Monitor database changes, check conditions and initiate actions.
* Dynamic behavior.
* "Event-Condition-Action" - when **event** occurs, check **condition**; if true, do **action**.
* Why use them:
    * Move the logic from the application to the DBMS.
    * Enforce constraints:
        * Not every case can be covered by the constraints.
        * Sometimes you can actually avoid throwing error from violated constraint and actually repair the data (in the **action** phase).