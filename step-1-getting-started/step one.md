todo: delete common.h
todo: give main a common interface
todo: main cmake needs to include the include folder
todo?: a cleanup script in esp32 repo
todo: migrate the make component script
.gitignore to contain sdkconfig.old

########### SETUP #############

https://github.com/PillarTechnology/getting-started-esp32.git

`git remote remove origin`

remove media, .github, docs, test/hardware_libraries, test/led_controller_tests.cpp, test/mocks/driver

in main.c take out lines 11-13 and 3-4

remove line 3&4 of main/CMakeLists.txt

########## hello world ###########

make a new component called app_logic
```
components/
    app_logic/
        include/
            app_logic.h
        app_logic.c
        CMakeLists.txt
        component.mk
```

remove board component and led controller component later

header should define an initialize function and a doWork function
main.c should include app_logic (cmake too)

write test for main calling init and dowork

runtests.sh to see red

add calls to app_main, test for green