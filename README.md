# QuickPlot folder
Here you can find the code to make the graph plots from .csv files.

Note that the macro needs as argument `(Double_t threshold_lower_limit,Double_t threshold_upper_limit, TString path_to_csv)` for the plots without the exponential fit, and `(Double_t time_start_fit, Double_t time_stop_fit, Double_t threshold_lower_limit,Double_t threshold_upper_limit, TString path_to_csv)`, where `[time_start_fit,time_stop_fit]` is the range in which ypu want to fit.


You can run the macro using the commands: 

  - `root -l -b 'quickplot.cpp(lower_threshold,upper_threshold,"csv_path_name")'` or  
    `root -l 'quickplot.cpp(lower_threshold,upper_threshold,"csv_path_name")'`.
  
  - `root -l -b 'quickplot.cpp(t_start,t_stop,lower_threshold,upper_threshold,"csv_path_name")'` or
    `root -l 'quickplot.cpp(t_start,t_stop,lower_threshold,upper_threshold,"csv_path_name")'`.

Note that with the flag -b root will operates in background so it wont open the shell and the interface while without it it will open the shell and the interface.


After that you will find in the Result folder the plots
