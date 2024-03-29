

class Node:
	def __init__(self,value=None,key=None,code=None,left=None,right=None):
		self.value = value
		self.key = key
		self.code = code
		self.left = left
		self.right = right

	def __str__(self):
		return 'Node <%s>: %s code: %s\n\tLeft: %s \n\tRight: %s\n'%(self.key,self.value,self.code,self.left,self.right)

	def __contains__(self,key):
		return key == self.key
	
	def propagateCode(self,node,code):
		if(node.code == None):
			node.code = code
		else:
			node.code = code + node.code
		if(node.left):
			node.propagateCode(node.left,code)
		if(node.right):
			node.propagateCode(node.right,code)

	def __add__(self,node2):
		self.propagateCode(self,'0')
		node2.propagateCode(node2,'1')

		return Node(self.value+node2.value,self.key+node2.key,self,node2)
