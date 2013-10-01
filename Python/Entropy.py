#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
 Calculate Entropy
 
 Powered by fenglinglu.

"""
from math import log
def Pick_Items(Attribute,Value,Attributes,Items):
    New_Items = []
    row = 0
    for Item in Items:
        col = len(Item)
        if not Attribute in Attributes:
            print("error!")
        if Item[Attributes.index(Attribute)] == Value:
            New_Items.append(Item)
            row = row  + 1
    return New_Items,col,row,Value

def Val_Entropy(Items,col,row):
    S = []
    for Item in Items:
        if not Item[col-1] in S:
            S.append(Item[col-1])
    S_Count = []
    S_Sum = 0
    for i in range(len(S)):
        count = 0
        for Item in Items: 
            if Item[col-1] == S[i]:
                count = count + 1
        S_Count.append(count)
    for i in range(len(S_Count)):
	    S_Sum = S_Sum + S_Count[i]
    P = S_Count
    I = 0.0
    for i in range(len(P)):
        if S_Sum == 0:
            pass
        else:
            P[i] = P[i] / S_Sum
            I = I - P[i] * log(P[i],2)
    return I
	
def Att_Entropy(Attribute,Attributes,Items):
    Val = []
    sum = 0
    I = 0
    for Item in Items:
	    sum = sum + 1
	    if not Item[Attributes.index(Attribute)] in Val:
		    Val.append(Item[Attributes.index(Attribute)])
    for i in range(len(Val)):
        New_Items,col,row,Value = Pick_Items(Attribute,Val[i],Attributes,Items)
        I_Val = Val_Entropy(New_Items,col,row)
        I = I + I_Val * row / sum
    return I,Val
