/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfig.h"

#if HAS_BED_PROBE

#include "../gcode.h"
#include "../../module/motion.h"
#include "../../module/probe.h"
#include "../../feature/bedlevel/bedlevel.h"
#include "../../module/delta.h"//新增
/**
 * G30: Do a single Z probe at the current XY
 *
 * Parameters:
 *
 *   X   Probe X position (default current X)
 *   Y   Probe Y position (default current Y)
 *   E   Engage the probe for each probe (default 1)
 */
void GcodeSuite::G30() {
  if(parser.seen('T'))//新增
  {
    TERN_(HAS_LEVELING, set_bed_leveling_enabled(false));
    remember_feedrate_scaling_off();
    const xy_pos_t pos_h = {0,0};
    const xy_pos_t pos_a = {-100,-60};
    const xy_pos_t pos_b = {100,-60};
    const xy_pos_t pos_c = {0,110};
    const float measured_h = probe.probe_at_point(pos_h, PROBE_PT_NONE, 1);
    report_current_position();
    do_blocking_move_to(0,0,50);
    const float measured_a = probe.probe_at_point(pos_a, PROBE_PT_NONE, 1);
    report_current_position();
    do_blocking_move_to(0,0,50);
    const float measured_b = probe.probe_at_point(pos_b, PROBE_PT_NONE, 1);
    report_current_position();
    do_blocking_move_to(0,0,50);
    const float measured_c = probe.probe_at_point(pos_c, PROBE_PT_NONE, 1);
    report_current_position();
    do_blocking_move_to(0,0,50);
    delta_height -= measured_h;
    const float max_endstop = max(max(measured_a,measured_b),measured_c);
    abc_float_t e_delta = { 0.0f };
    e_delta.set((measured_a - max_endstop ),(measured_b - max_endstop ),(measured_c - max_endstop ));
    delta_endstop_adj += e_delta;
    const float MAX_endstop = max(max(delta_endstop_adj.a,delta_endstop_adj.b),delta_endstop_adj.c);
    delta_endstop_adj.set((delta_endstop_adj.a - MAX_endstop),(delta_endstop_adj.b - MAX_endstop),(delta_endstop_adj.c - MAX_endstop));
    restore_feedrate_and_scaling();
  }
  else
  {
  const xy_pos_t pos = { parser.linearval('X', current_position.x + probe.offset_xy.x),
                         parser.linearval('Y', current_position.y + probe.offset_xy.y) };

  if (!probe.can_reach(pos)) return;

  // Disable leveling so the planner won't mess with us
  TERN_(HAS_LEVELING, set_bed_leveling_enabled(false));

  remember_feedrate_scaling_off();

  const ProbePtRaise raise_after = parser.boolval('E', true) ? PROBE_PT_STOW : PROBE_PT_NONE;
  const float measured_z = probe.probe_at_point(pos, raise_after, 1);
  if (!isnan(measured_z))
    SERIAL_ECHOLNPAIR("Bed X: ", pos.x, " Y: ", pos.y, " Z: ", measured_z);

  restore_feedrate_and_scaling();

  if (raise_after == PROBE_PT_STOW)
    probe.move_z_after_probing();

  report_current_position();
}
}

#endif // HAS_BED_PROBE
