-- telemetry_monitor.adb
with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Telemetry_Monitor is

   -- Define a safe range for altitude (meters)
   subtype Altitude_Range is Integer range 0 .. 100_000;

   -- Define a record for telemetry packet
   type Telemetry is
      record
         Altitude : Altitude_Range;
         Temperature : Integer; -- Degrees Celsius
      end record;

   -- Procedure to check telemetry status
   procedure Check_Telemetry(Data : Telemetry) is
   begin
      if Data.Altitude < 500 then
         Put_Line("⚠️  Warning: Altitude critically low!");
      elsif Data.Altitude > 80_000 then
         Put_Line("🚀 Altitude very high — upper atmosphere");
      else
         Put_Line("✅ Altitude within nominal bounds.");
      end if;

      if Data.Temperature < -40 or else Data.Temperature > 85 then
         Put_Line("🔥 Temperature out of safe range!");
      end if;
   end Check_Telemetry;

   -- Simulate incoming telemetry
   Sample : Telemetry;

begin
   -- Assign values (try changing these!)
   Sample.Altitude := 450;
   Sample.Temperature := -45;

   -- Check and print status
   Check_Telemetry(Sample);
end Telemetry_Monitor;

