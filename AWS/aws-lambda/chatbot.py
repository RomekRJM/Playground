# Copyright 2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License"). You may not
# use this file except in compliance with the License. A copy of the License is
# located at
#     http://aws.amazon.com/apache2.0/
#
# or in the "license" file accompanying this file. This file is distributed on
# an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
# express or implied. See the License for the specific language governing
# permissions and limitations under the License.

import logging
import subprocess

log = logging.getLogger()
handler = logging.StreamHandler()
formatter = logging.Formatter(
        '%(asctime)s %(name)-12s %(levelname)-8s %(message)s')
handler.setFormatter(formatter)
log.addHandler(handler)
log.setLevel(logging.DEBUG)


def run_cmd(cmd):
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    output = ''
    for line in p.stdout.readlines():
        output += line

    p.wait()
    return output


def lambda_handler(event, context):
    assert context
    log.debug(event)
    bot_event = event

    trigger_word = bot_event['trigger_word']
    raw_text = bot_event['text']
    command = raw_text.replace(trigger_word, '').strip()

    if len(command) < 1:
        return {
            'text': "Usage: `chatops <command>.`"
        }

    log.debug("[lambda_handler] comand:{0}".format(command))

    output = run_cmd(command)

    log.debug("[lambda_handler] output:{0}".format(output))

    return {
        'text': "{0}".format(output)
    }


lambda_handler({
    'trigger_word': 'chatops',
    'text': 'ps -ef | grep ps'
}, 'blabla')