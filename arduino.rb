require "serialport"
s1t = "Temperature_GF_Bed"
s2t = "Temperature_FF_Living"
ow0 = "Weather_Temperature"
ow1 = "Temperature_GF_Office"
domain = "http://mi2x.com:8080"
port_str = "/dev/ttyACM0"
baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE
sp = SerialPort.new(port_str,baud_rate,data_bits,stop_bits,parity)

while true do
i=0
off = false
out = false
bed = false
c=0
liv = false
  while(i=sp.gets.chomp)do
    if i.include? "OW1"
    value = i.split(" ").last
    system `curl "#{domain}/CMD?#{ow1}=#{value}"`
    off = true
    c = c+1
    puts "ow1"
    end
    if i.include? "OW0"
    value = i.split(" ").last
    system `curl "#{domain}/CMD?#{ow0}=#{value}"`
    out = true
    puts "ow0"
    c = c+1
    end
    if i.include? "Sensor2"
    value = i.split("|")
    system `curl "#{domain}/CMD?#{s2t}=#{value[1]}"`
    liv = true
    puts "sensor2"
    c = c+1
    end
    if i.include? "Sensor1"
    value = i.split("|")
    system `curl "#{domain}/CMD?#{s1t}=#{value[1]}"`
    puts value
    end
    puts off 
    puts out
    puts liv
    break if  liv == true && off == true && out == true
  end
  break if c >= 3
end

sp.close
