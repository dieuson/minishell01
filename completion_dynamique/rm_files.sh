# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rm_files.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/07 14:05:26 by dvirgile          #+#    #+#              #
#    Updated: 2016/06/27 10:44:14 by dvirgile         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

echo "delete *~";
find . -name "*~" -exec rm {} \;

echo "delete *.h.gch";
find . -name "*.h.gch" -exec rm {} \;

echo "delete #*#";
find . -name "#*#" -exec rm {} \;

echo "delete *#*";
find . -name "*#*" -exec rm {} \;

echo "delete ._*";
find . -name "._*" -exec rm {} \;