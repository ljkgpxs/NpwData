#! /bin/sh

cd ctrl
tar zcvf ../control.tar.gz ./
cd ..
cd data
tar zcvf ../data.tar.gz ./
cd ..
tar zcvf ipk.ipk data* de* contr*

