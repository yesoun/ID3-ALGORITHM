#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
 ID3 Alg
 
 Powered by fenglinglu.

"""

from ReadData import Read_Data
from Entropy import *
Attributes,Items,row,col = Read_Data('test.txt')
ROOT = 'ROOT'
def ID3(Attributes,Items,row,col,ROOT):
	#Step 1
	Entropy = Val_Entropy(Items,col,row)
	#Step 2
	Gain = {}
	for Attribute in Attributes[0:col - 1]:
		Att_E,Un_Used_Val = Att_Entropy(Attribute,Attributes,Items) 
		Gain[Attribute] = Entropy - Att_E   
	temp = 0
	for Attribute in Attributes[0:col - 1]:
		if Gain[Attribute] > temp:
			temp = Gain[Attribute]
			NODE = Attribute
			Un_Used_Att_E,BRANCH = Att_Entropy(Attribute,Attributes,Items) 
	LEAVES = []
	for Value in BRANCH:
		flag = []
		New_Items,col,row,Un_Used_Value = Pick_Items(NODE,Value,Attributes,Items)
		for Item in New_Items:
			if not Item[col - 1] in flag:
				flag.append(Item[col - 1])
		if len(flag) == 1:
			LEAVES.append(flag) 
		else:
			LEAVES.append([])
			ID3(Attributes,New_Items,row,col,Value)
			
	Tree = {'ROOT':ROOT,'NODE':NODE,'BRANCH':BRANCH,'LEAVES':LEAVES}
	print(Tree)
ID3(Attributes,Items,row,col,ROOT)