$t_total = "Not Benchmarked"
def benchmark
  b_time = Time.now
    yield
  f_time = Time.now
  t_total =  f_time - b_time
  $t_total =  "#{t_total.round(2)} seconds"
end
