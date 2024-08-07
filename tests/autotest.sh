#!/usr/bin/env bash

#__COLORES__
DEFAULT='\e[0m'
GREEN='\e[32m'
RED='\e[31m'

#__Variables__
bash_stdout="/tmp/bash_out.txt"
stdin="./mini_inputs.txt"
mini_stdout="/tmp/mini_out.txt"

#__bash__
bash -i $stdin > $bash_stdout

#__Minishell__
../minishell < $stdin > $mini_stdout

#Remove Readline prompt from the output
sed -i '/^Minishell%/d' $mini_stdout

#Compare stdouts
echo -e "${GREEN}(<): $bash_stdout \t${RED}(>): $mini_stdout ${DEFAULT}"
diff -F --suppress-common-lines $bash_stdout $mini_stdout
