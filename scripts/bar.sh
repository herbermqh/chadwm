#!/bin/bash

interval=0

cpu() {
  cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

  printf "^c#3b414d^ ^b#A3BE8C^ CPU"
  printf "^c#abb2bf^ ^b#414753^ $cpu_val"
}

# cpu() {
#   eval "$(mpstat | awk '{print $13}' | xargs | awk '{print "CPU_NOT_USE="$2}')"

#   printf "^c#3b414d^ ^b#A3BE8C^ CPU"
#   printf "^c#abb2bf^ ^b#414753^ $(echo "100-$CPU_NOT_USE"|bc -l)"
# }

temperature_cpu() {
  printf "^c#94af7d^ "
  printf "^c#94af7d^ $(sensors -u coretemp-isa-0000 | sed "s/.000//g" | awk '{print $2}' | xargs | awk '{print $3}')ºC"
}

# update_icon() {
#   printf "^c#94af7d^ "
# }

# pkg_updates() {
#   # updates=$(doas xbps-install -un | wc -l) # void
#   updates=$(checkupdates | wc -l)   # arch , needs pacman contrib
#   # updates=$(aptitude search '~U' | wc -l)  # apt (ubuntu,debian etc)

#   if [ -z "$updates" ]; then
#     printf "^c#94af7d^ Fully Updated"
#   else
#     printf "^c#94af7d^ $updates"" updates"
#   fi
# }

# battery
batt() {
  # printf "^c#81A1C1^  "
  # printf "^c#81A1C1^ $(acpi | sed "s/,//g" | xargs | awk '{if ($3 == "Discharging"){print $4; exit} else {print $4""}}')"
  printf "^c#81A1C1^ $(acpi | sed "s/%//g" | sed "s/,//g" |xargs | awk '{if ($3 == "Discharging"){print ""} else {if ($3 == "Full"){print ""}else{print ""}}}')"
  printf "^c#81A1C1^ $(acpi | sed "s/%//g" | sed "s/,//g" | xargs | awk '{print $4}')"
}

brightness() {

  backlight() {
    backlight="$(xbacklight -get)"
    echo -e "$backlight"
  }


  printf "^c#BF616A^  "
  printf "^c#BF616A^%.0f\n" $(backlight)
}

mem() {
  printf "^c#94af7d^  "
  printf "^c#94af7d^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

wlan() {
  case "$(cat /sys/class/net/w*/operstate 2>/dev/null)" in 
  up) printf "^c#BF616A^  ^d^%s";;
  down) printf "^c#BF616A^ 睊 ^d^%s";;
  esac
}

clock() {
  printf "^c#81A1C1^  "
  printf "^c#81A1C1^ $(date '+%a, %I:%M %p') "
}

while true; do

  # [ $interval == 0 ] || [ $(($interval % 3600)) == 0 ] && updates=$(pkg_updates)
  [ $interval == 0 ] || [ $(($interval % 3600)) == 0 ]
  interval=$((interval + 1))

  sleep 1 && xsetroot -name "$(temperature_cpu) $(batt) $(brightness) $(mem) $(wlan) $(clock)"
  # sleep 1 && xsetroot -name "$(update_icon) $updates $(batt) $(brightness) $(cpu) $(mem) $(wlan) $(clock)"
done
