#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
 Read raw data from test.txt
 
 Powered by fenglinglu.

"""

def Read_Data(name):
	f = open(name,'r')
	Attributes = f.readline()
	Attributes = Attributes.strip('\n')
	Attributes = Attributes.split(' ')
	col = len(Attributes)
	print("Here are the Attributes :")
	for Attribute in Attributes:
		print(' ',Attribute,end='')
	print()
	row = 0 
	Items = []
	Item = f.readline()
	Item = Item.strip('\n')
	if Item:
		while True:
			row = row + 1
			Item = Item.split(' ')
			Items.append(Item)
			Item = f.readline()
			Item = Item.rstrip('\n')
			if not Item:
				break
	print("There are %d Items in total." % row)
	print("Here are the Items :")
	for Item in Items:
		for val in Item:
			print(' ',val,end='')
		print()
	f.close()
	return Attributes,Items,row,col