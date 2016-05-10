# KdTree
Simple KdTree spacial structure.

- Interaction:
  * Click to add a new point.

---

- Algoirithm:

```
Node *buildKdTree(ini, end, points)
{
  sort points by k-n coordinate
  median = (ini + end)/2
  node.point = points[med]
  node.left  = buildKdTree(ini, median, points) 
  node.right = buildKdTree(median, fim, points) 
  return node
}
```

- Example of a kd-Tree construction:

![alt text](https://github.com/paulaceccon/kdTree/blob/master/Images/example.png)

- Screenshot:

![alt text](https://github.com/paulaceccon/kdTree/blob/master/Images/kdtree.png)
