'''
Author : Shubham Sangamnerkar
Roll   : 4351
Class  : BE-3

C++ >> python
Use python3 
'''
import random
import queue
from turtle import *
s = 8
class node:
	def __init__(self,val,child):
		self.val = val
		self.child = child
		self.child_ptr = [None]*child
MAX = (10**18)
def num():
	return random.randint(-100,100)

def random_number_of_branches():
	return 2
	#return random.randint(1,4)

def raw_alpha_beta(dept,motive,alpha,beta):
	if dept>=2:
		val = num()
		return (val,node(val,0)) #leaf
	if motive:
		best = -MAX
		children = random_number_of_branches()
		p = node(best,children)
		for i in range(children):
			child = raw_alpha_beta(dept+1,(motive^1),alpha,beta)
			p.child_ptr[i] = child[1]
			best = max(best,child[0])
			alpha = max(alpha,best)
			if alpha>=beta:
				break
		p.val = best
		return (best,p)
	else:
		best = MAX
		children = random_number_of_branches()
		p = node(best,children)
		for i in range(children):
			child = raw_alpha_beta(dept+1,(motive^1),alpha,beta)
			p.child_ptr[i] = child[1]
			best = min(best,child[0])
			beta = min(beta,best)
			if alpha>=beta:
				break
		p.val = best
		return (best,p)

def dfs(root):
	my_child_and_me = []
	my_child_and_me.append(str(root.val))
	child_only = []
	for i in root.child_ptr:
		if i!=None:
			temp_list = dfs(i)
			if isinstance(temp_list,list):
				for i in temp_list:
					child_only.append(i)
			else:
				child_only.append(temp_list)
	if len(child_only)>0:
		my_child_and_me.append(child_only)
	if len(my_child_and_me)==1: #leaf node
		return my_child_and_me[0]
	return my_child_and_me #any other node


def bfs(root):
	q = queue.Queue()
	q.put(root)
	while q.empty()==False:
		cur = q.get()
		print(str(cur.child)+" "+str(cur.val))
		for i in cur.child_ptr:
			if i!=None:
				q.put(i)

def cntstrs(list):
    return len([item for item in list if isinstance(item, str)])

def drawtree(tree, pos,dept,head=0):
    c = cntstrs(tree)
    while len(tree):
        goto(pos)
        item = tree.pop(0)
        if head:
            write(item,1)
            drawtree(tree.pop(0),pos,dept+1)
        else:
            if isinstance(item, str):
                newpos = ((pos[0] + s*c/4 - s*cntstrs(tree))*3.4, pos[1] - 15*s)
                down()
                goto((newpos[0], newpos[1] + 15))
                up()
                goto(newpos)
                write(item,1)
            elif isinstance(item, list):
                drawtree(item,newpos,dept+1)

def display_tree(string_arr):
	myWin = Screen()
	startpos = (0,200)
	up()
	drawtree(string_arr, startpos,0,1)
	myWin.exitonclick()

root = raw_alpha_beta(0,1,-MAX,MAX)[1]
bfs(root)
display_tree(dfs(root))

'''
No input needed
'''
