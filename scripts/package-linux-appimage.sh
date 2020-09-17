SCRIPT_PATH="${BASH_SOURCE[0]}"
mkdir -p brln.AppDir/usr/bin
mkdir -p brln.AppDir/usr/lib
mkdir -p brln.AppDir/usr/share
cp $1/bin/brln brln.AppDir/usr/bin/.
cp $1/_deps/libpd-src/libs/libpd.so brln.AppDir/usr/lib/.
cp -r `dirname "$SCRIPT_PATH"`/../cmake/share brln.AppDir/usr/.
cp `dirname "$SCRIPT_PATH"`/../cmake/share/applications/brln.desktop brln.AppDir/.
cp `dirname "$SCRIPT_PATH"`/../cmake/share/icons/brln.xpm brln.AppDir/.

# Get and run linuxdeployqt
wget -c https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod a+x linuxdeployqt-continuous-x86_64.AppImage

# Create AppImage using linuxdeployqt
export VERSION="0.1.0"
./linuxdeployqt-continuous-x86_64.AppImage ./brln.AppDir/usr/bin/brln -appimage

# Post process artifacts
brlnAppImage=brln-$VERSION-x86_64.AppImage
mkdir -p dist/brln-$VERSION-linux
mv brln-[0-9].* dist/.
mv dist/$brlnAppImage dist/brln-$VERSION-linux/brln
chmod +x dist/brln-$VERSION-linux/brln
cp -r $1/bin/pd dist/brln-$VERSION-linux/.
pushd dist && zip -r brln-$VERSION-linux.zip brln-$VERSION-linux/; popd
