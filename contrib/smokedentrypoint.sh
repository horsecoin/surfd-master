#!/bin/bash

echo /tmp/core | tee /proc/sys/kernel/core_pattern
ulimit -c unlimited

# if we're not using PaaS mode then start surfd traditionally with sv to control it
if [[ ! "$USE_PAAS" ]]; then
  mkdir -p /etc/service/surfd
  cp /usr/local/bin/steem-sv-run.sh /etc/service/surfd/run
  chmod +x /etc/service/surfd/run
  runsv /etc/service/surfd
else
  /usr/local/bin/startpaassurfd.sh
fi
