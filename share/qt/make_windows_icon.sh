#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/chbtoken.ico

convert ../../src/qt/res/icons/chbtoken-16.png ../../src/qt/res/icons/chbtoken-32.png ../../src/qt/res/icons/chbtoken-48.png ${ICON_DST}
