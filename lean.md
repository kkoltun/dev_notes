# Lean software development

## What is Lean?

Lean is a systematic method for
* minimizing waste;
* maximizing value to the customer.

## 7 Lean Development Principles

### Eliminate Waste

**Eliminate anything that does not add value to the customer.**

The seven wastes defined in the Toyota school of Lean manufacturing are:
* **Over-production**: manufacturing an item before it is required.
* **Unnecessary transportation**: moving inventory from place to place which puts it at risk for damage without adding the value.
* **Inventory**: holding inventory adds cost without adding any value to the customer. 
Excess inventory takes up valuable space, increases lead times and delays innovation.
* **Motion**: unnecessary movement of the workers on the shop floor costs.
* **Defects**: quality issues causing rework or scrap add tremendous costs to organizations.
Habitually find ways to eliminate sources of defects.
* **Over-processing**: using advanced, expensive tools to do what could be done with simpler tools.
* **Waiting**: when inventory waits between value-adding steps.

These principles can reformulated in terms of the software development process:
* **Unnecessary code or functionality**: does not add customer value, slows down feedback loops.
* **Starting more than can be completed**: adds unnecessary complexity to the system.
* **Delay in software development process**: delays time to customer.
* **Unclear or changing requirements**: result in rework, frustration, quality issues, lack of focus.
* **Bureaucracy**: delays speed.
* **Slow ineffective communication**: result in delays, frustrations and poor communication to stakeholders.
* **Partially done work**: does not add value to the customer or allow team to learn from work.
* **Defects and quality issues**: result in rework, abandoned work and poor customer satisfaction.
* **Task switching**: apart from poor work quality and delays, result in low team morale and communication breakdowns.

### Build Quality In

**Quality is everyone's job - not just QA's.**

This can be done with the following tools:
* **Pair programming**: combine skills and experience of two developers instead of one.
* **Test-driven development**: write criteria for code before writing the code to ensure it meets business requirements.
* **Incremental development and constant feedback**.
* **Minimize wait states**: reduce context switching, knowledge gaps and lack of focus.
* **Automation**: automate any tedious, manual process or any process prone to human error.

### Create Knowledge

**Provide the infrastructure to properly document and retain valuable learning.**

This can be done with the following tools:
* **Pair programming**;
* **Code reviews**;
* **Documentation**;
* **Project wiki**;
* **Thoroughly commented code**;
* **Knowledge sharing sessions**;
* **Using tools to manage requirements or user stories**.

### Defer Commitment

**Demonstrate responsibility by keeping the options open and continuously collecting information, rather than making decision without the necessary data.**

This means:
* Do not plan in excessive detail for months in advance.
* Do not commit to ideas or project without a full understanding of the business requirements.
* Collect and analyze information regarding any important decisions constantly.

### Deliver Fast

**Build a simple solution, put in front of the customers, enhance incrementally based on customer feedback.**

This means:
* **To make decisions, you need knowledge and context.**
* Do not think too far in advance about future requirements.
* Eliminate blockers with urgency.
* Do not over-think solutions and business requirements.

This does not mean:
* Releasing sloppy code (simple code is not sloppy code).
* Making fundamental decisions about architecture early, without knowledge.

### Respect People

**Respect for people by communicating proactively and effectively.**

This means:
* Encourage healthy conflict.
* Surface any work-related issues as a team.
* Empowering each other to do their best work.

### Optimize the whole

**Every business represents a value stream - the sequence of activities required to desing, produce and deliver a product or service.**

This means:
* **Identifying value streams** - how value flows though teams.
* **Optimizing value streams** - the goal is to deliver as much value to our customers as quickly as possible.

Optimizing may include:
* **Introducing multi-disciplined co-located product teams.**
* **Providing teams with everything they need to deliver a request from start to finish, without reference to other teams.**

#### Vicious cycles caused by suboptimization

1. **Releasing sloppy code for the sake of speed.**
* Sloppy code increases complexity of the code base and results in more defects.
* More defects cause more work that needs to be done.
* More work puts pressure on developers to deliver quickly.
* Pressure leads to releasing sloppy code.
2. **Overloading testers.**
* When testers are overloaded, the cycle between writing code and feedback from testers gets longer.
* With longer cycles, developers write more code that is not tested resulting in more defects.
* More defects result in more testing.

## Five habits of successful lean development - Mary Poppendieck

### Purpose

**Every employee should know the purpose of the work they are doing.**

Example of `Tandberg` in Norway:
* **every** employee knew the purpose of the company - *everything we do here to make it easy for people for communicate*;
* **every** employee knew their commitmend to the purpose of the company - *here is the problems I am going to solve this month*;
* **we make great stuff and we sell it** - developers and sales people are most valued in the company, everyone else is support.

Example of `Standard Life`:
* whole bunch of software was not used, analysts were not dealing with customer problem;
* developers were put in the business teams, which shortened the way from customer needs to implementation.

Example of `Wells Fargo Mortgage Processing`:
* the lean team asked for changes, but everybody has bigger fish to fry;
* developers were put in the lean teams, this way every requested change was implemented immediately.

Summary from above two:
* developer should go and see what is the real customer problem is;
* have developers talk directly to the customers, ask questions, model and discuss ideas - before and while they are developing product.

### Passion

This means:
* Think about flow and constant improvement.
* Care about the work you do, be passionate about it.
* *Clean code always looks like it was written by someone who cares.*

#### Deliberate practice

What makes people really good at what they do?
The Theory of Expertise: *the most accomplished people need around ten years of "deliberate practice" before becomming world-class.*
10 years or 10000 hours of practice 3 hours a day.

Deliberate practice is about:
* identify a specific area that needs improvement;
* devise or learn from a teacher a focused exercise - desinged to improve the skill;
* keep practicing repeatedly;
* obtain immediate feedback - adjust accordingly;
* focus on pushing the limits - expect repeated failures;
* practice regularly and intensely - perhaps three hours a day.

Deliberate practice includes:
* teacher and mentors;
* challenges - not repeating every day, doing things you are not good at;
* immediate feedback;
* persistence.

### Persistence

Dijkstra's challenge: *If you wan more effective programmers, you will discover that they should not waste their time debugging - they should not introduce bugs to start with.*

The challenge is about:
* **not allowing defect injection in the first place**;
* **not assuming that there will be defects**;
* **finding the defects as you code**.

Usually companies use 30%-50% of release cycle for freezing the code and testing the system.
This is an approach that **assumes that there are defects**.
Change it into finding defects early, learning from them and ending with only 10% of time for this type of testing.
When defects are found in that phase, this is not usual and should be learnt from and avoided.

**The biggest defect is tolerating defects.**

### Pride



### Profit



