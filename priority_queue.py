

from Binary_heap import BinaryHeap
from Node import Node

class PriorityQueue:
	def __init__(self):
		self.order = BinaryHeap()

	def __str__(self):
		temp = self.order.copyHeap()
		front = temp.delete()
		string = ("<Front>\n")
		while front:
			string += (" %s"%front)
			front = temp.delete

		string += "<Back>"
		return string

	def enQueue(self,Node):
		self.order.insert(Node)
	def deQueue(self):
		return self.order.delete()

