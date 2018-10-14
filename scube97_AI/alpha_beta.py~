'''
Author : Shubham Sangamnerkar
Roll   : 4351
Class  : BE-3

C++ >> python
Use python3 
'''
import random
import queue
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

def bfs(root):
	q = queue.Queue()
	q.put(root)
	while q.empty()==False:
		cur = q.get()
		print(str(cur.child)+" "+str(cur.val))
		for i in cur.child_ptr:
			if i!=None:
				q.put(i)

root = raw_alpha_beta(0,1,-MAX,MAX)[1]
bfs(root)

'''
No input needed
'''
