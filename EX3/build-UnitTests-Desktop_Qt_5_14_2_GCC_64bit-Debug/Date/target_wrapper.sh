#!/bin/sh
LD_LIBRARY_PATH=/opt/lintula/Qt/5.14.2/5.14.2/gcc_64/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}
export LD_LIBRARY_PATH
QT_PLUGIN_PATH=/opt/lintula/Qt/5.14.2/5.14.2/gcc_64/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}
export QT_PLUGIN_PATH
exec "$@"
