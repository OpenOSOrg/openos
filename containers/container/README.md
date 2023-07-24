# Description

Master_Container_Test.yml contains all the appropriate image, build, gdb and UI tests compressed into one for the OPE repository base container image



## Setup-and-Build

Responsible for building the image, pushing the beta image to the registry of quay.io, and recording the time and size of the build. All other jobs wait for this to complete before beginning.


## Health-Check

Test pulls the beta image and runs it, after some time executes  a health status check to veridy if the container is up and running.


## Image-Version-Check

Test pulls the beta image and runs it, then queries the image json to ensure the proper image and tag are used.


## JupyterNB-Test

Test pulls the beta image and runs it. Starts up jupyter lab server in the container and then runs test.ipynb which verfies import of necessary packages. If error does not occur when executing notebook, behaving as expected.


## Package-Version-Test

Test pulls the beta image and runs it. Checks what version of packages are installed within the running container and then passes that to version_check.py to compare the current list with a stable list (versions.txt) and finds any inconsistencies.


## Checksum

Checksum verifies that the checksum of the container image is correct.


## Size-and-Time-Display

Test pulls the beta image and runs it (needed for size)This test uses the build time recorded in the build to display this time and also queries the image to find its size and display that. 


## UI-Test

This test infrastructure uses selenium to run functionality and visual checks on jupyter notebook running in the image. It pulls the beta image and runs it. Then, the url is passed to rise_test.py which is then used to do the functionality testing with selenium and record screenshots for the visual / formatting veriication test. After this, the screenshot difference test is triggered which runs screenshots_diff.py for final format checking.


## GDB-Test

Test pulls the beta image and runs it. It then runs a bash sript calling gdb 100 times to check functionality. If gdb error will throw here. Lastly, rights the output of the script to text file that then verifies the corrrect number of instructions have been executed.


## Approval

Sends approval authorization request to approved authorization, test then waits for authorization has been granted to proceed. 


## Publish

This test publishes the latest stable base image to the OPE quay.io repo


## NOTE
In order to push / pull to the appropriate quay.io repo you must update registry_user and registry_password to the correct corresponding variables


