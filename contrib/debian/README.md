
Debian
====================
This directory contains files used to package tpcd/tpc-qt
for Debian-based Linux systems. If you compile tpcd/tpc-qt yourself, there are some useful files here.

## tpc: URI support ##


tpc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install tpc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your tpcqt binary to `/usr/bin`
and the `../../share/pixmaps/tpc128.png` to `/usr/share/pixmaps`

tpc-qt.protocol (KDE)

