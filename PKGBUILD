# $Id: pkgbuild-mode.el,v 1.23 2007/10/20 16:02:14 juergen Exp $
# Maintainer: Michael Manley <mmanley@NTE-WRKSTN-2.NASUTEK-CORE.NISN.nasutek.com>
pkgname=nasutek-commander  
pkgver=5.0
pkgrel=1 
pkgdesc="A Total Commander-like application written in Qt for Windows, Linux, and Mac OS X. It is a continuation of Beesoft Commander."
url="http://commander.nasutek.org/"
arch=('i686' 'x86_64')
license=('Apache')
depends=(qt)
makedepends=(cmake)
conflicts=()
replaces=()
backup=()
install=
source=(http://assets.nasutek.org/srcpkg/nc/$pkgname-$pkgver-src.tar.bz2)
md5sums=()
build() {
  cd $startdir/src/$pkgname-$pkgver-src
  mkdir output
  cd output
  cmake -DCMAKE_INSTALL_PREFIX:PATH=$startdir/pkg ..
  make || return 1
  make install
}
