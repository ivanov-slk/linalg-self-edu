import tensorflow as tf

print(tf.__version__)

# (AB)^T = A^T * B^T
a = tf.constant([1.2, 3.4, -5.7, -5.3, 8.7, 4.127], shape=(2, 3))

b = tf.constant([34.5, 234.34, 876.43, -5.1243, -675.234, 54.2], shape=(3, 2))

abt = tf.transpose(tf.matmul(a, b))
atbt = tf.matmul(tf.transpose(b), tf.transpose(a))
print(abt)
print(atbt)