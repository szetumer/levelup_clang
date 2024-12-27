CC = gcc

test_samples: test_samples.c samples.c ../../proto/proto.c ../../proto/strs.c ../../proto/ints.c ../../proto/str.c ../../proto/base.c
	$(CC) -o test_samples test_samples.c samples.c ../../proto/proto.c ../../proto/strs.c ../../proto/ints.c ../../proto/str.c ../../proto/base.c /usr/local/lib/libcalg.a

test: test.c samples.c ../../proto/proto.c ../../proto/strs.c ../../proto/ints.c ../../proto/str.c ../../proto/base.c
	$(CC) -o test test.c samples.c ../../proto/proto.c ../../proto/strs.c ../../proto/ints.c ../../proto/str.c ../../proto/base.c /usr/local/lib/libcalg.a
