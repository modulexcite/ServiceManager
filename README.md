# System XVI

![System XVI Logo](doc/logotype.png)


### Discontinuation

Dear System XVI Community,

I have today made the decision to discontinue work on S16.

This decision has been made following a period of inactivity and an obsoletion
of System XVI's practical raison d'être with Michael Heily's ReLaunchD and other
efforts in service management.

System XVI technology remains, by a great margin, the most innovative design of a
service management suite ever publicly shown. Only SystemD and Illumos' SMF come
close - and both have flaws, particularly SystemD.

I am today convinced that the future of computing lays in the great legacy left
by Kristen Nygaard and Alan Kay (though we, their heirs, have fucked it up.)

S16's design - in line with the Kayian principles of object-orientation - reified
the message, and in many respects the components of S16 act somewhat like objects.
The future for research in a modern service management system must be built atop
such principles.

I may pursue such research at some point, and it may be under the banner of S16.
But for now I have other focuses. I invite those who were interested in S16 to
try to pursue such research. I would welcome anything from a fork of S16 to a
new service manager incorporating similar principles, and I would likely
contribute to it.

Ça ira.
- D.M.

##### Development note

**In short: S16 development will be slow for a while.**

I am sorry to report that S16 development is going to be reduced in pace for
the next while. 

I have not taken this decision lightly. My hope had been to power ahead on S16
work to produce a usable system within just 2 months of founding the project.
Illness and associated stress has forced my hand in abandoning this target.

I want to be explicit in saying that I do not have - nor have I ever had - any
intention to stop work on S16. I can't envision any likely cause for that in
the near future. To those watching with eager mind the development of S16; do
not worry. You will surely see something in the coming months.

### Overview

**A note: please be aware that System XVI is not yet a usable system.**

System XVI is a modern take on service management.  It aims to incorporate
useful functionality while maintaining a modular design in the UNIX tradition.

We have an IRC channel; find it at irc://irc.freenode.net/systemxvi

This project is still in an active phase of development. It is *not yet possible* to boot
with S16; indeed, the init subdirectory is a placeholder.  All effort is
currently focused on bringing the various components up to a level where they
are able to act as a service supervisor tool capable of running simple,
forking, and oneshot systemd units.

##### The Four Motives of S16

 * Interface-orientation: the system should be designed to fit a clean and
   stable interface. The interface should come before the implementation.
 * Separation of concerns: individual components should not do much alone, but
   work in concert to create a grand system.
 * Pluggable modularity: components should be easily replaceable and
   extensible.
 * Self-healing: components that crash should be able to restart without
   forgetting system state or otherwise causing breakage.

From those four motives emerges a naturally clean and lightweight system.

Please find a flowchart depicting the key components' actions and interactions
[here](doc/s16.png).

### Development

##### Building
System XVI uses kBuild (as used in VirtualBox, etc).  There are a minimal
number of dependencies:

###### Linux dependencies
 * libkqueue
 * rpcgen
 * libtirpc

###### All-platform dependencies
 * kBuild

Note that some of these packages may need to be affixed with -devel on systems
that are not source-based.

Having installed the appropriate dependencies, you can then build S16 simply:
just run `kmk` in the source directory. You will find binaries under **out/**.

##### Licence
System XVI is free software. You may use it and its source code under the terms
of the Revised BSD licence; this is reproduced in full in
[doc/COPYRIGHT.md](doc/COPYRIGHT.md).

### FAQ
A few frequently asked questions about S16:

> On what platforms does S16 run?

 * FreeBSD
 * DragonFly BSD
 * GNU+Linux
 * muslibc+BusyBox+Linux

It is likely that this will run on all of the other BSD systems as well.

> Why is it bigger than sinit?

Because System XVI's scope is greater than sinit. sinit simply initialises a
system sufficiently to call into /etc/rc or similar.  In contrast, S16 is a
service management system first and foremost, and an extensible one at that.

> Why do you like to use macros for simple tasks?

Because I don't like to type.

> Why do you use so many typedefs?

As above.

> What are your problems with systemd?

In a word: architectural. systemd is tightly integrated in a way that makes
pluggable replacements difficult. It also tends toward a monolithic design.
Whilst systemd's PID 1 may not be as big as some claim - systemd is, after all,
split into 69 binaries - it still includes complex logic for parsing
configuration files, handling D-Bus calls, a transactional dependency
resolution system, et al.

### Testimonials
System XVI has received unexpected publicity. Several commentators have written
these glowing endorsements of System XVI:

> This is probably the best example I've seen on how NOT to program in C.
> Unneeded typedefs, random macros for simple logic. Do not use.

 - /u/nwmcsween, reddit.

> It wont work, trust me.

 - /u/Risar, reddit, on the future functionality of System XVI.

> There's a lot of good reasons why this project will never be an alternative
> to systemd (or even a good piece of software in it's own right), and they're
> pretty much all shown during a discussion with the author on Rizon. [link to
> the main S16 developer drunkenly arguing with someone about code style.]

 - /u/TheReverend403, reddit.

> [...] the world doesn't like goto. First of all, it can cause all kinds of
> memory leaks.

> Your program is simply an attacker's target.

> As soon as a distro maintainer sees that goto, it'll be rejected.

 - vitimiti, 4chan-associated IRC channel #/g/technology

> System XVI definitely is not it: It looks like a design-by-comitee 
> architecture based on the buzzwords of 1980s (sunRPC, yeah), implemented
> by an amateur. It is addressing the wrong problem (cross-platform) and the
> whole design is targeted at that, preventing it from ever reaching feature
> parity with systemd on Linux. At least it is consistently bad everywhere.
> That is progress, we never had such a system before, ever.

 - Phoronix commentor
