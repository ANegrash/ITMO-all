%define next_el 0

%macro colon 2
    %ifid %2
        %2: dq next_el
    %else
        %error "Second arg must be id"
    %endif
    %ifstr %1
        db %1, 0
    %else
        %error "First arg must be str"
    %endif
    %define next_el %2
%endmacro