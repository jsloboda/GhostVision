Fs = 8000;
audiorecorder(Fs,16,1);
record(ans);
pause(10);
stop(ans);
getaudiodata(ans);