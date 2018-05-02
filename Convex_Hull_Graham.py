import numpy as np
import matplotlib.pyplot as plt
import functools

pivot = None

def orientation(p1,p2,p3):
	val = (p3[1]-p2[1])*(p2[0]-p1[0])-(p2[1]-p1[1])*(p3[0]-p2[0])

	if(val == 0):
		return 0
	if(val>0):
		return 2
	else:
		return 1

def distance(p1,p2):
	return (p1[1]-p2[1])*(p1[1]-p2[1])+(p1[0]-p2[0])*(p1[0]-p2[0])


def PIVOTSORT(p1,p2):
	o = orientation(pivot,p1,p2)
	if(o==0):
		if(distance(pivot,p1) >= distance(pivot,p2)):
			return -1
		else:
			return 1

	if(o==2):
		return 1
	else:
		return -1

def next_to_top(s):
	val = s.pop()
	ret = s.pop()
	s.append(ret)
	s.append(val)
	return ret

def convex_hull(points):
	n = len(points)

	ppo = np.array(points)
	ymin = points[0][1]
	mini = 0

	for i in range(n):
		y = points[i][1]
		if((y<ymin) or ((y==ymin) and points[i][0] < points[mini][0])):
			ymin = y
			mini = i

	points[0],points[mini] = points[mini],points[0]
	global pivot
	pivot = points[0]

	points[1:] = sorted(points[1:],key=functools.cmp_to_key(PIVOTSORT),reverse=True)

	points_new = []

	points_new.append(points[0])
	hullnp = np.array(points_new)
	plt.clf()
	plt.plot(hullnp[:,0],hullnp[:,1],'b-',picker=5)
	plt.plot(ppo[:,0],ppo[:,1],".r")
	plt.axis('off')
	plt.show(block=False)
	plt.pause(0.1)
	ii = 1
	while(ii<n):
		while(ii<n-1 and orientation(pivot,points[ii],points[ii+1])==0):
			ii = ii+1
		if(ii<n):
			points_new.append(points[ii])
			hullnp = np.array(points_new)
			plt.clf()
			plt.plot(hullnp[:,0],hullnp[:,1],'b-',picker=5)
			plt.plot(ppo[:,0],ppo[:,1],".r")
			plt.axis('off')
			plt.show(block=False)
			plt.pause(0.1)
		ii = ii + 1

	hullnp = np.array(points_new)
	plt.clf()
	plt.plot(hullnp[:,0],hullnp[:,1],'b-',picker=5)
	plt.plot(ppo[:,0],ppo[:,1],".r")
	plt.plot([hullnp[-1,0],hullnp[0,0]],[hullnp[-1,1],hullnp[0,1]],'b-',picker=5)
	plt.axis('off')
	plt.show(block=False)
	plt.pause(0.1)
	s = []
	s.append(points_new[0])
	s.append(points_new[1])
	s.append(points_new[2])

	m = len(points_new)

	hullnp = np.array(s)
	plt.clf()
	plt.plot(hullnp[:,0],hullnp[:,1],'b-',picker=5)
	plt.plot(ppo[:,0],ppo[:,1],".r")
	plt.axis('off')
	plt.show(block=False)
	plt.pause(0.1)

	for i in range(3,m):
		while(orientation(next_to_top(s),s[-1],points_new[i])!=2):
			s.pop()
		s.append(points_new[i])
		hullnp = np.array(s)
		plt.clf()
		plt.plot(hullnp[:,0],hullnp[:,1],'b-',picker=5)
		plt.plot(ppo[:,0],ppo[:,1],".r")
		plt.axis('off')
		plt.show(block=False)
		plt.pause(0.1)
		
	print(s)
	return s


points = [[0,3],[1,1],[2,2],[4,4],[0,0],[1,2],[3,1],[3,3]]

s = convex_hull(points)

print('convex_hull')
ppo = np.array(points)
hullnp = np.array(s)
plt.clf()
plt.plot(hullnp[:,0],hullnp[:,1],'b-',picker=5)
plt.plot(ppo[:,0],ppo[:,1],".r")
plt.plot([hullnp[-1,0],hullnp[0,0]],[hullnp[-1,1],hullnp[0,1]],'b-',picker=5)
plt.axis('off')
plt.show(block=False)
plt.pause(1)
print('Stop')



