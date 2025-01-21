#Parallel Processes
The purpose of this file is to run two c programs at the same time that interact with one another in very simple ways. Program a creates a bit of shared memory and increments it indefinitely. Process b finds that memory and bumps it however much you want it to. The cli for each are the following:

./a [int hm key id] [optional: 'd']
-- writing [shm key id] d will delete the memory. You must re-create the memory from scratch each time you use it.
./b [int shm key id] [int bump amount]
-- if your shm key doesn't match, you won't be able to bump anything. (ie, b cannot create any memory, only use memory that has already been created.)
-- the bump amount is the amount that a's counter will be adjusted by.