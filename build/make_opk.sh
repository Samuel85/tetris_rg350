#!/bin/sh

OPK_NAME=tetris.opk

echo ${OPK_NAME}

# create default.gcw0.desktop
cat > default.gcw0.desktop <<EOF
[Desktop Entry]
Name=Tetris
Comment=Tetris for the RG350
Exec=tetris
Terminal=false
Type=games
StartupNotify=true
Icon=icon
Categories=games
X-OD-NeedsDownscaling=true
EOF

# create opk
FLIST="tetris ./fonts ./images ./music"
FLIST="${FLIST} default.gcw0.desktop"
FLIST="${FLIST} icon.png"

rm -f ${OPK_NAME}
mksquashfs ${FLIST} ${OPK_NAME} -all-root -no-xattrs -noappend -no-exports

cat default.gcw0.desktop
rm -f default.gcw0.desktop
