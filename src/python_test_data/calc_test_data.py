import tensorflow as tf

print(tf.__version__)

# (AB)^T = A^T * B^T
a = tf.constant([1.2, 3.4, -5.7, -5.3, 8.7, 4.127], shape=(2, 3))

b = tf.constant([34.5, 234.34, 876.43, -5.1243, -675.234, 54.2], shape=(3, 2))

abt = tf.transpose(tf.matmul(a, b))
atbt = tf.matmul(tf.transpose(b), tf.transpose(a))
# print(abt)
# print(atbt)

# norms
# print(tf.norm(a, ord=1, axis=(0, 1)))
# print(tf.norm(a, ord='fro', axis=(0, 1)))

a1 = tf.constant([1.2, 3.4, -5.7, -5.3, 8.7, 4.127], shape=(1, 6))
print(tf.norm(a1, ord=1))
print(tf.norm(a1))

b1 = tf.constant([34.5, 234.34, 876.43, -5.1243, -675.234, 54.2], shape=(6, 1))
# print(tf.norm(b, ord=1, axis=(0, 1)))
# print(tf.norm(b, ord='fro', axis=(0, 1)))
print(tf.norm(b1, ord=1))
print(tf.norm(b1))

# QR decomposition
qr_data = tf.constant([12, -51, 4, 6, 167, -68, -4, 24, -41], shape=(3, 3))
qr_data = tf.cast(qr_data, tf.float64)
print(tf.linalg.qr(qr_data))

qr_data_r = tf.constant([12, -51, 4, 6, 167, -68, -4, 24, -41, 10, -24, 8],
                        shape=(4, 3))
qr_data_r = tf.cast(qr_data_r, tf.float64)
print(tf.linalg.qr(qr_data_r))