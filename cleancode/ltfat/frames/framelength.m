function L=framelength(F,Ls);
%FRAMELENGTH  Frame length from signal
%   Usage: L=framelength(F,Ls);
%
%   FRAMELENGTH(F,Ls) returns the length of the frame F, such that
%   F is long enough to expand a signal of length Ls.
%
%   If the frame length is longer than the signal length, the signal will be
%   zero-padded by FRANA.
%
%   If instead a set of coefficients are given, call FRAMELENGTHCOEF.
%
%   See also: frame, framelengthcoef
%
%   Url: http://ltfat.sourceforge.net/doc/frames/framelength.php

% Copyright (C) 2005-2014 Peter L. Søndergaard <soender@users.sourceforge.net>.
% This file is part of LTFAT version 1.4.4
%
% This program is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
%
% This program is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
%
% You should have received a copy of the GNU General Public License
% along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
L=F.length(Ls);

