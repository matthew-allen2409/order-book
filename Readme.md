# Simple High Throughput Realtime Order Book

### Features
- Supports Bid and Ask orders.
- Allows order insertion, modification, and deletion.
- Matches orders on insertion to maintain the current state of the book at all times.
- Modifying an order's price will reset its position in the order queue.

### Performance  
This order book achieves sub-microsecond order processing via careful selection of data structures.

### TODOS
- Clean up some occurences of repeated code.
- Experiment with utilizing thread pools and synchronization mechanisms / lock free structures.
- Tests! (I wrote this is a couple of sessions and am unfamiliar with c++ testing frameworks. Most tests were performed manually in modifying the main.cc code.)
