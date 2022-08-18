A1 Appendix FAQs
================

A1.1 Compilation errors
-----------------------

Cannot build the application:

-  Make sure you are on the correct esp-idf branch/release. Run ``git submodule
   update —init —recursive`` to make sure the submodules are at the
   correct heads
-  Make sure you are on the correct ESP Zigbee SDK branch.
-  Delete the build/ directory and also sdkconfig and sdkconfig.old and
   then build again.

A1.2 Flashing errors
--------------------

Cannot flash to the target:

- Make sure you have connected your device to the PC.
- Checking the port, run ``ls -la /dev/ttyUSB*`` to check corresponding port is recognized by PC.
- Make sure you choose the correct target.

