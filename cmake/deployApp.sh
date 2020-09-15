SCRIPT_PATH="${BASH_SOURCE[0]}"
mkdir -p brln.AppDir/usr/lib
cp -r $1/bin brln.AppDir/usr/bin
cp $1/_deps/libpd-src/libs/libpd.so brln.AppDir/usr/lib/.
cp $1/_deps/libpd-src/libs/libpd.so brln.AppDir/usr/lib/.
cp -r `dirname "$SCRIPT_PATH"`/share brln.AppDir/usr/share
cp `dirname "$SCRIPT_PATH"`/share/applications/brln.desktop brln.AppDir/.
cp `dirname "$SCRIPT_PATH"`/share/icons/hicolor/400x400/brln.png brln.AppDir/.

# Get and run linuxdeployqt
wget -c https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod a+x linuxdeployqt-continuous-x86_64.AppImage

# Create AppImage using linuxdeployqt
./linuxdeployqt-continuous-x86_64.AppImage ./brln.AppDir/usr/bin/brln -appimage
