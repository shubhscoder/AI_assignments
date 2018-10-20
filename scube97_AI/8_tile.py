'''
Author : Shubham Sangamnerkar
Roll   : 4351
Class  : BE-3

C++ >> python
Use python3 
'''
import queue as q
import math
import copy
class game:
	def __init__(self):
		self.n=0
		self.initial_state = []
		self.final_state = []
		self.visited = set()
		self.st = q.PriorityQueue()
		self.num_pos = {}
		self.trace_game = {}
		self.flag = 0
		print("Enter the size of the board")
		self.n=int(input())
		print("Enter initial state of the board")
		for i in range(self.n):
			l = list(map(int,input().split(" ")))
			self.initial_state.append(l)
		print("Enter final state of the board")
		for i in range(self.n):
			l = list(map(int,input().split(" ")))
			self.final_state.append(l)
		for i in range(self.n):
			for j in range(self.n):
				self.num_pos[self.final_state[i][j]] = (i,j)

	def isvalid(self,i,j):
		if i<0 or i>=self.n or j<0 or j>=self.n:
			return False
		return True

	@staticmethod
	def print_grid(board):
		for i in board:
			for j in i:
				print(j,end=" ")
			print()

	@staticmethod
	def zero_pos(board):
		for i in range(len(board)):
			for j in range(len(board)):
				if board[i][j]==0:
					return (i,j)

	def move_generator(self,board):
		moves = []
		for i in range(self.n):
			for j in range(self.n):
				if board[i][j]==0:
					if self.isvalid(i-1,j):
						moves.append((i-1,j))
					if self.isvalid(i+1,j):
						moves.append((i+1,j))
					if self.isvalid(i,j-1):
						moves.append((i,j-1))
					if self.isvalid(i,j+1):
						moves.append((i,j+1))
		return moves

	def heuristic(self,game_state):
		cost = 0
		for i in range(self.n):
			for j in range(self.n):
				pos = self.num_pos[game_state[i][j]]
				cost+=(abs(i-pos[0])+abs(j-pos[1]))
		return cost

	def is_destination(self,game_state):
		for i in range(self.n):
			for j in range(self.n):
				if game_state[i][j]!=self.final_state[i][j]:
					return False
		return True

	@staticmethod
	def tuple_for_list(board):
		tuple_of_tuple = tuple(tuple(i) for i in board)
		return tuple_of_tuple

	@staticmethod
	def list_for_tuple(board):
		list_of_list = [list(i) for i in board]
		return list_of_list		

	def game_play(self):
		iterations = 0
		self.st.put(((0,0),game.tuple_for_list(self.initial_state)))
		self.trace_game[game.tuple_for_list(self.initial_state)] = game.tuple_for_list(self.initial_state)
		while self.st.qsize()>0:
			current_node = self.st.get()
			board = game.list_for_tuple(current_node[1])
			if game.tuple_for_list(board) in self.visited:
				continue
			self.visited.add(game.tuple_for_list(board))
			if board==self.final_state:
				print("Moves required : "+str(current_node[0][1]))
				self.flag = 1
				return
			moves = self.move_generator(board)
			pos_zero = game.zero_pos(board)
			for i in moves:
				duplicate = copy.deepcopy(board)
				temp = duplicate[pos_zero[0]][pos_zero[1]]
				duplicate[pos_zero[0]][pos_zero[1]] = duplicate[i[0]][i[1]]
				duplicate[i[0]][i[1]] = temp
				if game.tuple_for_list(duplicate) not in self.visited:
					ht = current_node[0][1]
					self.trace_game[game.tuple_for_list(duplicate)] = game.tuple_for_list(board)
					self.st.put(((ht+1+self.heuristic(duplicate),ht+1),game.tuple_for_list(duplicate)))
			iterations+=1
			if iterations>100000:
				return 

	def print_move_sequence(self):
		if self.flag!=1:
			print("Not solvable")
			return
		move_sequence = []
		cur = game.tuple_for_list(self.final_state)
		while cur!=self.trace_game[cur]:
			move_sequence.append(cur)
			cur = self.trace_game[cur]
		move_sequence.append(self.initial_state)
		move_sequence.reverse()
		for i in move_sequence:
			game.print_grid(i)
			print()

khelo = game()
khelo.game_play()
khelo.print_move_sequence()

'''
refer input.txt for input
'''
