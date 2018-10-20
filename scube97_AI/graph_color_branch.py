'''
Author : Shubham Sangamnerkar
Roll   : 4351
Class  : BE-3

C++ >> python
Use python3
'''
import queue
import copy
class graph:
	def __init__(self):
		self.n = int(input("Enter number of vertices:"))
		self.edges = int(input("Enter number of edges:"))
		self.m = int(input("Enter max number of colors that can be used:"))
		self.adj = [[] for i in range(self.n)]
		self.color = [-1 for i in range(self.n)]

	def input_graph(self):
		for i in range(self.edges):
			x,y = map(int,input().split(" "))
			x-=1
			y-=1
			self.adj[x].append(y)
			self.adj[y].append(x)

	def valid(self,current,color_assigned,color):
		for i in self.adj[current]:
			if color[i]==color_assigned:
				return False
		return True

	def clear_graph(self):
		for i in range(self.n):
			self.color[i] = -1

	def is_end(self,coloring):
		if -1 not in coloring:
			return True
		return False

	def colors_used(self,coloring):
		return max(coloring)+1

	def possible_colors(self,coloring):
		p = []
		for i in coloring:
			if i!=-1:
				p.append(i)
		return p

	def color_graph(self):
		current_best = self.n
		q = queue.Queue()
		color = [-1 for i in range(self.n)]
		color[0] = 0 #color the first vertex with the 0th color
		q.put(color)
		itera = 0
		while q.qsize()>0:
			itera+=1
			current = q.get()
			if self.is_end(current): #if all vertices are colored
				if current_best>=self.colors_used(current): #they are colored with less colors than what the current sol gave
					current_best = self.colors_used(current) #change current_best
					self.color = copy.deepcopy(current)
					continue
			possible_colors = self.possible_colors(current)
			#try assigning a color that is already used
			for i in range(self.n):
				if current[i]==-1:#if 
					for j in possible_colors:
						duplicate = copy.deepcopy(current)
						if self.valid(i,j,duplicate):
							duplicate[i] = j
							if self.colors_used(duplicate)<=current_best: #expand only if the this expandsion can give a solution better than current
								q.put(duplicate)
					#try assigning a new color
					duplicate = copy.deepcopy(current)
					duplicate[i] = self.colors_used(duplicate)
					if self.colors_used(duplicate)<=current_best:
						q.put(duplicate)
	def print_sol(self):
		for i in self.color:
			print(i,end= " ")
		print()

banao = graph()
banao.input_graph()
banao.color_graph()
if banao.colors_used(banao.color)<=banao.m:
	banao.print_sol()
else:
	print("Solution not possible with the given M")
	print("Atleast "+str(banao.colors_used(banao.color))+" colors are required to color the give graph")