flash:
    cd ~/dev/qmk_firmware && \
        qmk flash \
            -kb crkbd/rev1 \
            -km r0nsha \
            -e USER_NAME=holykeebs \
            -e OLED=stock \
            -j8

clone_firmware:
    git clone --recurse-submodules https://github.com/holykeebs/qmk_firmware.git ~/dev/qmk_firmware -b hk-master
    # cd ~/dev/qmk_firmware
    # mkdir -p modules
    # git submodule add https://github.com/getreuer/qmk-modules.git modules/getreuer
    # git submodule update --init --recursive

install:
    #!/usr/bin/env bash
    if ! command -v qmk &> /dev/null; then
        python3 -m pip install --user qmk
    fi
    mkdir -p ~/dev
    qmk setup --home ~/dev/qmk_firmware -b hk-master holykeebs/qmk_firmware
    make clean; bear -- qmk compile -kb crkbd/rev1 -km r0nsha

bear:
    make clean; bear -- qmk compile -kb crkbd/rev1 -km r0nsha
