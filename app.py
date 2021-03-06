#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Control Equisense Coffee Machine from Slack.

Released under MIT License. See LICENSE file.
By Yoan Tournade <yoan@ytotech.com>
"""
import time
from slackclient import SlackClient
# Add your Slack API token in a token.py file:
# SLACK_TOKEN = 'YOUR_SLACK_API_TOKEN'
from token import SLACK_TOKEN

USER_COFFEE = '@uslackbot'
CMD_COFFEE = ['coffee', u'café', 'court', 'short', 'long']
COFFEE_SHORT = ['short', 'court']
COFFEE_LONG = ['long']

slack = SlackClient(SLACK_TOKEN)
if not slack.rtm_connect():
	raise RuntimeError('Invalid token')

def talk(message, channel='#hackathon_eqs'):
	slack.api_call(
		"chat.postMessage", channel=channel, text=message,
		username='Eqs Coffee Machine', icon_emoji=':coffee:'
	)

def isShort(message):
	return any(a in message for a in COFFEE_SHORT)

def isLong(message):
	return any(a in message for a in COFFEE_LONG)

print('Listening to Slack...')
while True:
	notifications = slack.rtm_read()
	# [{u'text': u'coin', u'ts': u'1458399795.000050', u'user': u'U03RVKZTA',
	# u'team': u'T03228R4X', u'type': u'message', u'channel': u'C0Q2FPFQD'}]
	for notification in notifications:
		if notification['type'] != 'message' and not 'text' in notification:
			continue
		print(notification)
		message = notification['text'].lower()
		if not USER_COFFEE in message or not any(a in message for a in CMD_COFFEE):
			continue
		if not isShort(message) and not isLong(message):
			talk('Here I am! Which kind of coffee do you want?')
		if isShort(message):
			talk('One short coffee ordered!')
		if isLong(message):
			talk('A long coffee for a long day: that\'s on the way!')
	time.sleep(1)
