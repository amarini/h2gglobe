#!/bin/bash

for dir in ${USER}_* ; 
  do 
  cp -v  $dir/CMS-HGG.root CMS-HGG_`echo $dir | sed 's/amarini_//'`_$(date +%Y_%m_%d).root; 
  done

###### END ##### 
