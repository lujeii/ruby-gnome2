# Copyright (C) 2013  Ruby-GNOME2 Project Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

module Clutter
  module Threads
    class << self
      alias_method :add_timeout_full, :add_timeout
      def add_timeout(interval_or_priority, interval=nil, &block)
        if interval.nil?
          priority, interval = GLib::PRIORITY_DEFAULT, interval_or_priority
          add_timeout_full(priority, interval, &block)
        else
          priority = interval_or_priority
          add_timeout_full(priority, interval, &block)
        end
      end

      alias_method :add_idle_full, :add_idle
      def add_idle(priority=nil, &block)
        priority ||= GLib::PRIORITY_DEFAULT_IDLE
        add_idle_full(priority, &block)
      end
    end
  end
end
