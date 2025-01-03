grammar turtle;

start : expr | <EOF> ;

expr     : 'G01' x_cord=NUMBER y_cord=NUMBER #G01LinearInterpolation
         | 'G28' x_cord=NUMBER y_cord=NUMBER #G28ZeroReturn
         | 'F' speed=NUMBER #setFeedRate
         | 'M03' #M03SpindleStartClockwise
         | 'M05' #M05SpindleStop
         ;
NUMBER : ('0' .. '9') + ('.' ('0' .. '9') +)? ;
WS : [ \r\n\t]+ -> skip;
COMMENT : '#' ~[\r\n]* -> skip ;