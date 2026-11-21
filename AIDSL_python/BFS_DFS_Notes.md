### Graph Representation

| Property            | Matrix       | List           |
| ------------------- | ------------ | -------------- |
| Space               | \(O(V^2)\)   | \(O(V+E)\)     |
| Edge lookup         | \(O(1)\)     | \(O(\deg(v))\) |
| Neighbour traversal | \(O(V)\)     | \(O(\deg(v))\) |
| Best suited for     | Dense graphs | Sparse graphs  |