# 3D Repo Asset Guru
3D Repo Mobile Asset Management System

[![YouTube](https://img.youtube.com/vi/Kc24mj9f2gY/0.jpg)](https://www.youtube.com/watch?v=Kc24mj9f2gY)

## Dependencies

* Libdmtx: http://libdmtx.sourceforge.net/
For compilation instructions, see wiki: http://libdmtx.wikidot.com/libdmtx-on-windows-using-visual-studio
Available is also pre-compiled Windows-32 binary: https://sourceforge.net/projects/libdmtx/files/libdmtx/0.7.2-binaries/

## Android Compilation

1) Make sure your Qt installation has the necessary Android packages. You can change them in Windows:
```
Start menu > Add or Remove Programs > Qt > Modify 
```

2) Install Android Studio and install the additional SDK/NDK as required:
```
Android Studio > Tools > Android > SDK Manager > Tabs for SDK Platforms and SDK Tools
```
(make sure to tick Android SDK Tools, Google USB Driver and NDK)

3) Install JDK: http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html
(you do not need Apache Ant as that has been deprecated in Qt)

4) Setup your Android devices in Qt Creator:
```
Tools > Options > Devices > Android
```
Add paths to SDK, NDK, etc

5) Make sure your Android device is plugged in and recognised:
```
> cd c:\Users\jozef\AppData\Local\Android\sdk\platform-tools\
> adb devices
```

### Additional Resources
* Getting started with Qt for Android: http://doc.qt.io/qt-5/androidgs.html
* Connecting Android devices: http://doc.qt.io/qtcreator/creator-developing-android.html
* Qt platform notes for Android: http://doc.qt.io/qt-5/platform-notes-android.html
* Deploying on Android: http://doc.qt.io/qt-5/deployment-android.html

