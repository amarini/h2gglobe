#!/bin/bash
 python remove_cat.py -f hgg_card_massfacmva_legacy_binned_v1.txt  -o tmp_hgg.txt -c cat5 -p ZH
 python remove_cat.py -f tmp_hgg.txt  -o tmp2_hgg.txt -c cat6 -p ZH
 python remove_cat.py -f tmp2_hgg.txt  -o tmp3_hgg.txt -c cat5 -p WH
 python remove_cat.py -f tmp3_hgg.txt  -o tmp4_hgg.txt -c cat6 -p WH
 python remove_cat.py -f tmp4_hgg.txt  -o tmp5_hgg.txt -c cat11 -p qqH
 python remove_cat.py -f tmp5_hgg.txt  -o tmp6_hgg.txt -c cat11 -p ggH
 python remove_cat.py -f tmp6_hgg.txt  -o tmp7_hgg.txt -c cat8 -p ggH
 python remove_cat.py -f tmp7_hgg.txt  -o tmp8_hgg.txt -c cat9 -p ggH
 python remove_cat.py -f tmp8_hgg.txt  -o tmp9_hgg.txt -c cat8 -p qqH
 python remove_cat.py -f tmp9_hgg.txt  -o tmp10_hgg.txt -c cat8 -p ttH
 python remove_cat.py -f tmp10_hgg.txt  -o tmp11_hgg.txt -c cat11 -p ZH
 python remove_cat.py -f tmp11_hgg.txt  -o tmp12_hgg.txt -c cat11 -p WH
