/****************************************************************
 *  TI UtilLib.ConsoleUtility namespace: Useful Console Utils   *
 *  (C) 2007, Texas Instruments, Inc.                           *
 *                                                              *
 * Author:  Daniel Allred                                       *
 *                                                              *
 ****************************************************************/

using System;
using System.Text;

namespace UtilLib.ConsoleUtility
{
    public enum Position : uint
    {
        NONE = 0,
        TOP,
        BOTTOM,
        RIGHT,
        LEFT,
    }
    
    public class ProgressBar
    {
        #region Private Variables

        private Int32 posYBar, posXBar;
        private Int32 posYPercent,posXPercent;
        private Int32 posYText, posXText;
        private Int32 barWidth, totalWidth;
        private Position percPosition, textPosition;
        private Double percent;
        private String text;

        #endregion

        #region Private Properties

        private Position PercentPosition
        {
            get
            {
                return percPosition;
            }
            set
            {
                if ((value == Position.BOTTOM) || (value == Position.TOP))
                    percPosition = Position.LEFT;
                else
                    percPosition = value;
            }
        }

        private Position TextPosition
        {
            get
            {
                return textPosition;
            }
            set
            {
                if ((value == Position.RIGHT) || (value == Position.LEFT))
                    textPosition = Position.BOTTOM;
                else
                    textPosition = value;
            }
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// Set the percentage completeness of the progress bar.
        /// </summary>
        public Double Percent
        {
            get
            {
                return percent;
            }
            set
            {
                percent = (value > 1) ? 1 : value;
                UpdatePercent();
                if (percent == 1)
                {
                    Console.WriteLine();
                    Console.CursorVisible = true;
                }
            }
        }

        /// <summary>
        /// Set the status text field
        /// </summary>
        public String Text
        {
            get
            {
                return text;
            }
            set
            {
                text = value;
                UpdateText();
            }
        }
        #endregion

        #region Class Constructors
        /// <summary>
        /// Default constructor
        /// </summary>
        public ProgressBar():this(60)
        {
        }

        /// <summary>
        /// Variable-width ProgressBar constructor
        /// </summary>
        /// <param name="charWidth">Width of progress bar.</param>
        public ProgressBar(Int32 charWidth): this(charWidth,Position.LEFT,Position.BOTTOM)
        {
        }

        /// <summary>
        /// Variable-width and variable percent location ProgressBar constructor
        /// </summary>
        /// <param name="charWidth">Width of status bar in characters.</param>
        /// <param name="pos">StatusPosition enum value.</param>
        /// <param name="percentPos">Position enum for Percentage location.</param>
        /// <param name="txtPos">Position enum for the text location.</param>
      
        public ProgressBar(Int32 charWidth, Position percentPos, Position textPos)
        {
            // Make sure we are starting on a clean, new line           
            if (Console.CursorLeft != 0)
                Console.WriteLine();
            
            // Set private member values
            PercentPosition = percentPos;
            TextPosition = textPos;
            barWidth = charWidth;
            percent = 0.0;
            
            //Make the cursor invisible
            Console.CursorVisible = false;

            // Place initial fields
            if (TextPosition == Position.TOP)
            {
                posYText = Console.CursorTop;
                posXText = Console.CursorLeft;
                Console.WriteLine("Status Undefined");
            }
            if (PercentPosition == Position.LEFT)
            {
                posXPercent = Console.CursorLeft;
                posYPercent = Console.CursorTop;
                Console.Write(" {0,3:D}% ", 0);
            }
            
            Console.Write("[ ");
            posYBar = Console.CursorTop;
            posXBar = Console.CursorLeft;
            for (int i = 0; i < barWidth; i++)
            {
                Console.Write("-");
            }
            Console.Write(" ]");
            
            if (PercentPosition == Position.RIGHT)
            {
                posXPercent = Console.CursorLeft;
                posYPercent = Console.CursorTop;                
                Console.Write(" {0,3:D}% ", 0);
            }
            totalWidth = Console.CursorLeft;

            if (Console.CursorLeft != 0)
                Console.WriteLine();
            if (TextPosition == Position.BOTTOM)
            {
                posYText = Console.CursorTop;
                posXText = Console.CursorLeft;                
                Console.WriteLine("Status Undefined");
            }

            //Go to a new line so any future text can be placed
            Console.WriteLine();
        }
        #endregion

        #region Class methods

        #region Public functions
        public void Update(Double percent, String status)
        {
            Percent = percent;
            Text = status;
        }
        #endregion

        #region Private helper functions
        private void UpdatePercent()
        {
            // Save current cursor position
            int oldCursorTop = Console.CursorTop, oldCursorLeft = Console.CursorLeft;
            
            // Update the precent if needed
            if (PercentPosition != Position.NONE)
            {
                Console.SetCursorPosition(posXPercent,posYPercent);
                Console.Write(" {0,3:D}% ", (Int32)(Percent*100));
            }

            // Update the progress bar
            Console.SetCursorPosition(posXBar,posYBar);
            ConsoleColor oldBackGroundColor = Console.BackgroundColor;
            Console.BackgroundColor = Console.ForegroundColor;
            Int32 numOfBlocks = (Int32)Math.Floor(barWidth * Percent);
            Console.Write("".PadLeft(numOfBlocks,' '));
            Console.BackgroundColor = oldBackGroundColor;
            
            // Reset the cursor location            
            Console.SetCursorPosition(oldCursorLeft, oldCursorTop);
        }

        private void UpdateText()
        {
            int oldCursorTop = Console.CursorTop, oldCursorLeft = Console.CursorLeft;

            // Update the text field
            if (TextPosition != Position.NONE)
            {
                Console.SetCursorPosition(posXText, posYText);
                if (text.Length < totalWidth)
                    Console.Write(text.PadLeft((totalWidth + text.Length) / 2));
                else
                    Console.Write(text);
            }
            
            // Reset the cursor location            
            Console.SetCursorPosition(oldCursorLeft, oldCursorTop);
        }
        #endregion

        #endregion

    }
}