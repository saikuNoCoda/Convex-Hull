import numpy as np
import matplotlib.pyplot as plt

def orientation(p1,p2,p3):
	val = (p3[1]-p2[1])*(p2[0]-p1[0]) - (p2[1]-p1[1])*(p3[0]-p2[0])

	if(val == 0):
		return 0
	if(val>0):
		return 2
	else:
		return 1

def Convex_Hull(points):
	n = len(points)
	hull = []
	ppo = np.array(points)
	left = 0
	for i in range(n):
		if(points[i][0] < points[left][0]):
			left = i

	p = left

	while True:
		hull.append(points[p])

		q = (p+1)%n
		for i in range(n):
			if( orientation(points[p],points[i],points[q]) == 2):
				q = i

		p = q

		hullnp = np.array(hull)
		plt.clf()
		plt.plot(hullnp[:,0],hullnp[:,1],'b-',picker=5)
		plt.plot(ppo[:,0],ppo[:,1],".r")
		plt.axis('off')
		plt.show(block=False)
		plt.pause(0.1)

		if(p == left):
			plt.clf()
			plt.plot(hullnp[:,0],hullnp[:,1],'b-',picker=5)
			plt.plot(ppo[:,0],ppo[:,1],".r")
			plt.plot([hullnp[-1,0],hullnp[0,0]],[hullnp[-1,1],hullnp[0,1]],'b-',picker=5)
			plt.axis('off')
			plt.show(block=False)
			plt.pause(0.1)
			break

	for point in hull:
		print(point)
	return np.array(hull)
	
def main():
	points = [[0,3],[2,2],[1,1],[2,1],[3,0],[0,0],[3,3]]
	hull = Convex_Hull(points)
	points = np.array(points)

	plt.clf()
	plt.figure()
	plt.plot(hull[:,0],hull[:,1],'b-',picker=5)
	plt.plot([hull[-1,0],hull[0,0]],[hull[-1,1],hull[0,1]],'b-',picker=5)
	plt.plot(points[:,0],points[:,1],".r")

	plt.axis('off')
	plt.show()

main()