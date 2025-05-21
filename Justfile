flash:
    cd ~/dev/qmk_firmware && \
        qmk flash \
            -kb crkbd/rev1 \
            -km r0nsha \
            -e USER_NAME=holykeebs \
            -e OLED=stock \
            -j20

install:
    python3 -m pip install --user qmk
    mkdir -p ~/dev
    qmk setup --home ~/dev/qmk_firmware -b hk-master holykeebs/qmk_firmware
    make clean; bear -- qmk compile -kb crkbd/rev1 -km r0nsha
