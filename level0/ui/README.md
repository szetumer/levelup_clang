#info on ncurses

brew info ncurses
==> ncurses: stable 6.5 (bottled) [keg-only]
Text-based UI library
https://invisible-island.net/ncurses/announce.html
Installed
/usr/local/Cellar/ncurses/6.5 (4,052 files, 9.6MB)
  Poured from bottle using the formulae.brew.sh API on 2025-01-28 at 11:57:31
From: https://github.com/Homebrew/homebrew-core/blob/HEAD/Formula/n/ncurses.rb
License: MIT
==> Dependencies
Build: pkgconf ✔
==> Caveats
ncurses is keg-only, which means it was not symlinked into /usr/local,
because macOS already provides this software and installing another version in
parallel can cause all kinds of trouble.

If you need to have ncurses first in your PATH, run:
  echo 'export PATH="/usr/local/opt/ncurses/bin:$PATH"' >> ~/.zshrc

For compilers to find ncurses you may need to set:
  export LDFLAGS="-L/usr/local/opt/ncurses/lib"
  export CPPFLAGS="-I/usr/local/opt/ncurses/include"

For pkg-config to find ncurses you may need to set:
  export PKG_CONFIG_PATH="/usr/local/opt/ncurses/lib/pkgconfig"
==> Analytics
install: 74,875 (30 days), 216,072 (90 days), 970,572 (365 days)
install-on-request: 1,324 (30 days), 4,059 (90 days), 21,698 (365 days)
build-error: 137 (30 days)
