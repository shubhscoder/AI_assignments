'''
Author : Shubham Sangamnerkar
Roll   : 4351
Class  : BE-3

C++ >> python
Use python3 
'''
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

	def clear_graph(self):
		for i in range(self.n):
			self.color[i] = -1

	def valid(self,current,color_assigned):
		for i in self.adj[current]:
			if self.color[i]==color_assigned:
				return False
		return True

	def color_graph(self,current):
		if current==self.n:
			return True
		for i in range(self.m):
			if self.valid(current,i):
				self.color[current] = i
				if self.color_graph(current+1)==True:
					return True
				self.color[current] = -1
		return False

	def print_sol(self):
		for i in self.color:
			print(i,end=" ")
		print()

	def get_minimum_m(self):
		for i in range(1,self.n+1):
			self.clear_graph()
			self.m = i
			if banao.color_graph(0):
				return i


banao = graph()
banao.input_graph()
if banao.color_graph(0):
	banao.print_sol()
else:
	print("No solution possible with given M")

print("Minimum number of colors required : "+str(banao.get_minimum_m()))


'''
Sample Input1:
n:4
edges:6
max colors:3
graph:
1 2
1 3
1 4
2 3
2 4
3 4

Sample Input2:
n:4
edges:6
max colors:4
graph:
1 2
1 3
1 4
2 3
2 4
3 4
'''