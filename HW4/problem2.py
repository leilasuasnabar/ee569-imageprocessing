# ---------------------------
# EE 569 Assignment 4
# Date: 04/23/17
# Name: Leila Suasnabar
# ID: 3109-9816-56
# email: lsuasnab@usc.edu
# ---------------------------
# Some input parameters set up where obtained from the Tensorflow.org website
# For instance, the exponential learning rate, shuffle_batch, and overall reading
# data set up were modified from tensorflow.org
# https://www.tensorflow.org/programmers_guide/reading_data
# and cifar10_input.py
#
# Also, tf.tut.py and tutorial3.py were used as a guideline to set up the CNN

import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
from tensorflow.contrib.layers import flatten
import myFunctions as my

# Exponential Learning Rate parameters
learning_rate = 0.1
decay_rate = 0.96
decay_steps = 300

# Set model parameters
iterations = 17000
batch_size = 128
prob = 0.2 #used for the dropout function

display_step = 50
logs_path = './logFiles'
yaxis = np.array([],dtype = 'float')
yaxisTr = np.array([],dtype = 'float')

# Model parameters
n_input = 32*32*3
n_classes = 10

# Get data
print('\n------ Setting up the Data -------')
# Set up the data to be used by batches
train_images, train_labels = my.getCifarData2(batch_size, 'Training')
test_images, test_labels = my.getCifarData2(batch_size, 'Testing')

def conv2d(x, W, b, strides=1):
    # Conv2D wrapper, with bias and relu activation
    x = tf.nn.conv2d(x, W, strides=[1, strides, strides, 1], padding='SAME')
    x = tf.nn.bias_add(x, b)
    return tf.nn.relu(x)

def maxpool2d(x, k=2):
    # MaxPool2D wrapper
    return tf.nn.max_pool(x, ksize=[1, k, k, 1], strides=[1, k, k, 1],
                          padding='SAME') #With Padding

def conv_net(x, weights, biases):
    # Convolutional Layer
    conv1 = conv2d(x, weights['wc1'], biases['bc1'])
    # Dropout
    conv1 = tf.nn.dropout(conv1,prob)
    # Max Pooling
    conv1 = maxpool2d(conv1)
    # Local Response Normalization
    conv1 = tf.nn.lrn(conv1, depth_radius=5, bias=2.0, alpha=1e-3, beta=0.75)

    # Convolutional Layer 2
    conv2 = conv2d(conv1, weights['wc2'], biases['bc2'])
    # Dropout
    conv2 = tf.nn.dropout(conv2,prob)
    # Max Pooling
    conv2 = maxpool2d(conv2)
    # Local Response Normalization
    conv2 = tf.nn.lrn(conv2, depth_radius=5, bias=2.0, alpha=1e-3, beta=0.75)

    # Fully Connected Layer 1
    # Reshape conv2 output to fit fully connected layer input
    fc1 = flatten(conv2)
    fc1 = tf.add(tf.matmul(fc1, weights['wd1']), biases['bd1'])
    fc1 = tf.nn.relu(fc1)
    
    # Fully connected layer 2
    fc2 = tf.add(tf.matmul(fc1, weights['wd2']), biases['bd2'])
    fc2 = tf.nn.relu(fc2)
    
    # Output, class prediction
    out = tf.add(tf.matmul(fc2, weights['wout']), biases['bout'])
    return out 

weights = {
    # 5x5 conv, 3 input/channel, 64 filters
    'wc1' : tf.get_variable('wc1',dtype = tf.float32,shape=[5, 5, 3, 64],initializer=tf.contrib.layers.xavier_initializer()),
    # 5x5 conv, 64 inputs/channel, 64 filters
    'wc2' : tf.get_variable('wc2',shape=[5, 5, 64, 64],initializer=tf.contrib.layers.xavier_initializer()),
    # 5x5 conv, 64 inputs/channel, 128 filters
    #'wc3' : tf.get_variable('wc3',shape=[5, 5, 64, 128],initializer=tf.contrib.layers.xavier_initializer()),
    # fully connected 1, 576 inputs, 120 outputs
    'wd1' : tf.get_variable('wd1',shape=[2304, 120],initializer=tf.contrib.layers.xavier_initializer()),
    # fully connected 2, 120 inputs, 84 outputs
    'wd2' : tf.get_variable('wd2',shape=[120, 84],initializer=tf.contrib.layers.xavier_initializer()),
    # 84 input, 10 outputs (class prediction)
    'wout' : tf.get_variable('wout',shape=[84, n_classes],initializer=tf.contrib.layers.xavier_initializer())
}

biases = {
    'bc1' : tf.get_variable('bc1',shape=[64],initializer=tf.contrib.layers.xavier_initializer()),
    'bc2' : tf.get_variable('bc2',shape=[64],initializer=tf.contrib.layers.xavier_initializer()),
    #'bc3' : tf.get_variable('bc3',shape=[128],initializer=tf.contrib.layers.xavier_initializer()),
    'bd1' : tf.get_variable('bd1',shape=[120],initializer=tf.contrib.layers.xavier_initializer()),
    'bd2' : tf.get_variable('bd2',shape=[84],initializer=tf.contrib.layers.xavier_initializer()),
    'bout' : tf.get_variable('bout',shape=[n_classes],initializer=tf.contrib.layers.xavier_initializer())
}

with tf.variable_scope('Model') as scope:
    # Training data
    pred = conv_net(train_images, weights, biases)
    scope.reuse_variables()
    # Test data
    pred_test = conv_net(test_images, weights, biases)

# Loss
with tf.name_scope('Loss'):
    def getLoss(pred, y):
        return tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits=pred, labels=tf.squeeze(tf.cast(y, tf.int32))))
    loss = getLoss(pred, train_labels)

# Optimizer
with tf.name_scope('SGD'):
    def SGD(cost):
        # Using exponential decay to obtain the model learning rate
        # Modified code from: Tensorflow.org
        global_step = tf.Variable(0, trainable=False)
        learning_rate_new = tf.train.exponential_decay(learning_rate, global_step,
                                                         decay_steps, decay_rate, staircase=True)
        # Create optimizer
        optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate_new).minimize(cost)
        return optimizer
    optimizer = SGD(loss)

# Accuracy
with tf.name_scope('Accuracy'):
    def accuracy(pred, y):
        predicted_correctly = tf.equal(tf.cast(tf.argmax(pred, 1), tf.int32), tf.squeeze(tf.cast(y, tf.int32)))
        accuracy = tf.reduce_mean(tf.cast(predicted_correctly, tf.float32))
        return accuracy
    accuracy_testing = accuracy(pred_test, test_labels)
    accuracy_training = accuracy(pred,train_labels)

# Create a summary
loss_data = tf.summary.scalar("Loss",loss)
accuracy_training_data = tf.summary.scalar("Accuracy Training",accuracy_training)
mergedSummary = tf.summary.merge([accuracy_training_data,loss_data])

accuracy_testing_data = tf.summary.scalar("Accuracy Testing", accuracy_testing)
mergedSummaryTest = tf.summary.merge([accuracy_testing_data])

# Initializing the variables
print('--- Initializing the Variables ---')
init = tf.global_variables_initializer()
print('---------- Training CNN ----------\n')

with tf.Session() as sess:
    sess.run(init)

    # op to write logs to Tensorboard
    trainSummary = tf.summary.FileWriter(logs_path+'/train',graph=tf.get_default_graph())
    testSummary = tf.summary.FileWriter(logs_path+'/test')
    
    # Since we're not using placeholders:
    tf.train.start_queue_runners(sess=sess)

    for i in range(iterations):
        _, cost = sess.run([optimizer, loss])
    
        if (i+1) % display_step== 0:
            # Find train accuracy
            train_accuracy, summary = sess.run([accuracy_training,mergedSummary])
            trainSummary.add_summary(summary, i+1)

            # Find test accuracy
            test_accuracy, summaryTest = sess.run([accuracy_testing,mergedSummaryTest])
            testSummary.add_summary(summaryTest, i+1)
            yaxisTr = np.append(yaxis,[train_accuracy])
            yaxis = np.append(yaxisTr,[test_accuracy])

    # Save Data
    np.savetxt('dataTest.txt',yaxis,fmt='%3f')
    np.savetxt('dataTrain.txt',yaxisTr,fmt='%3f')
    print("Optimization Finished!")
    trainSummary.close()
    testSummary.close()
